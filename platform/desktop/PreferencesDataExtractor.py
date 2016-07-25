
import sys
import xml.etree.ElementTree as ET

def getColorValue(aValue):
    
    value = str(aValue)

    if len(value) > 2:
        raise ValueError
    
    colorValue = int(value, 16) / 255
    
    return colorValue

if __name__ == '__main__':

    argc = len(sys.argv)

    if (argc == 2):
        tree = ET.parse(sys.argv[argc - 1])
        root = tree.getroot()
        
        for r1 in root:
            for r2 in r1:
                attribute = dict(r2.attrib)
                variable_name = ''
                variable_value = ''
    
                if '{http://schemas.android.com/apk/res/android}title' in attribute:
                    variable_name = attribute['{http://schemas.android.com/apk/res/android}title']
                    variable_name = variable_name.replace('@string/prefs_', '')
                    variable_name = variable_name.replace('_title', '')
                if '{http://schemas.android.com/apk/res/android}defaultValue' in attribute:
                    variable_value = attribute['{http://schemas.android.com/apk/res/android}defaultValue']
                    if 'color' in variable_name:
                        variable_value = variable_value.replace('#', '')
                        value = '{'
                        for i in range(0, len(variable_value), 2):
                            value = '{} {:.2},'.format(value, getColorValue(variable_value[i:i + 2]))
                        value = value[:len(value) - 1]
                        value = '{} {}'.format(value, '}')
                        variable_value = '{}; //#{}'.format(value, variable_value)
                    else:
                        variable_value = '{};'.format(variable_value)
                        
                print('{0} = {1}'.format(variable_name, variable_value))