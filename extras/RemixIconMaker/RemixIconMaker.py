import re
import base64
import requests

endl = "\n"

regex_icon_description = re.compile(r'(.ri-[^{]+:before ){([^}]+)}$', re.MULTILINE)
regex_icon_name = re.compile(r'.ri-(.+):before.+', re.MULTILINE)
regex_icon_unicode = re.compile(r'.+content: "\\(.+)";', re.MULTILINE)


def get_icon_names(icon_description):
    return re.findall(regex_icon_name, icon_description[0])


def get_icon_unicode(icon_description):
    return re.findall(regex_icon_unicode, icon_description[1])


def parse_css(css_content, output_file):
    match = re.findall(regex_icon_description, css_content)
    for icon_description in match:
        icon_names = get_icon_names(icon_description)
        icon_unicode = get_icon_unicode(icon_description)
        for icon_name in icon_names:
            write_icon_description(icon_name, icon_unicode[0], output_file)


def camel_case_string(string):
    result = ""
    words = string.split("-")
    for word in words:
        result += word.capitalize()
    return result


def write_icon_file_header(output_file):
    output_file.write("// IMPORTANT! This file is auto-generated see extras/RemixIconMaker" + endl)
    output_file.write(endl)
    output_file.write("#pragma once" + endl)
    output_file.write("using Icon = juce::String;" + endl)
    output_file.write(endl)


def write_icon_description(icon_name, icon_unicode, output_file):
    output_file.write("const Icon RemixIcon_" + camel_case_string(icon_name) + " = Icon::fromUTF8(u8\"\\u" + icon_unicode + "\");" + endl)


def write_font_file_header(font, output_file):
    output_file.write("// IMPORTANT! This file is auto-generated see extras/RemixIconMaker" + endl)
    output_file.write(endl)
    output_file.write("#pragma once" + endl)
    output_file.write(endl)
    output_file.write("namespace RemixIconData {" + endl)
    output_file.write("\textern const char*\tremixiconwebfont_ttf;" + endl)
    output_file.write("\tconst int\t\t\tremixiconwebfont_ttfSize = " + str(len(font)) + ";" + endl)
    output_file.write("}" + endl)


def write_font_file_source(font, output_file):
    output_file.write("// IMPORTANT! This file is auto-generated see extras/RemixIconMaker" + endl)
    output_file.write(endl)
    output_file.write("#include \"RemixIconData.h\"" + endl)
    output_file.write(endl)
    output_file.write("static const unsigned char data[] = {")
    count = 0
    size = len(font)
    for byte in font:
        count += 1
        size -= 1
        if (count % 40) != 39:
            output_file.write(str(byte))
        else:
            output_file.write(str(byte)  + endl)
        if size > 0:
            output_file.write(",")
    output_file.write("};" + endl)
    output_file.write("const char* RemixIconData::remixiconwebfont_ttf = (const char*) data;" + endl)


def get_file_from_github(user, repo_name, path_to_file):
    url = 'https://api.github.com/repos/{0}/{1}/contents/{2}'.format(user, repo_name, path_to_file)
    req = requests.get(url)

    if req.status_code == requests.codes.ok:
        req = req.json()
        byte_content = req['content'].encode()
        decoded_data = base64.b64decode(byte_content)
        return decoded_data
    else:
        print('File {path_to_file} was not found.')
        exit(-1)

css = get_file_from_github('Remix-Design', 'RemixIcon', 'fonts/remixicon.css').decode("utf-8") 
font = get_file_from_github('Remix-Design', 'RemixIcon', 'fonts/remixicon.ttf')


icon_file = open("Icons.h", "wt")
write_icon_file_header(icon_file)
parse_css(css, icon_file)
icon_file.close()


font_file_header = open("RemixIconData.h", "wt")
font_file_source = open("RemixIconData.cpp", "wt")
write_font_file_header(font, font_file_header)
write_font_file_source(font, font_file_source)
font_file_header.close()
font_file_source.close()