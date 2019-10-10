import subprocess
def check(expr, result):
    out = subprocess.run(['./calc', expr], stdout=subprocess.PIPE)
    if out.stdout.decode('ascii') != result:
        print('error {0} != {1}, got {2}'.format(expr, result, out.stdout))
    else:
        print('test {0} = {1} ok!'.format(expr, result))
print('operations:')
check('2 + 2', '4\n')
check('2 * 8', '16\n')
check('10 - 55', '-45\n')
check('15 / 3', '5\n')
check('2 + -1', '1\n')
print('priority:')
check('2 + 3 * 4 - -2', '16\n')
check('3 - 4 / 2 + -6', '-5\n')
print('zero division')
check('1 / 0', 'error on character 0\n')
print('invalid input')
check('1 +* 2', 'error on character *\n')
check('1.2 + 3', 'error on character .\n')
check('2 + ', 'error on character \0\n')
check('+2', 'error on character +\n')
check('2 /% 5', 'error on character %\n')
check('2 --- 1', 'error on character -\n')
