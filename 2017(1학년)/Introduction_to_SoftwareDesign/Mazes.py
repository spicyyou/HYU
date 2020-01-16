#-*- coding: cp949 -*-��
MAZE=[['#','#','#','#','#','#','#','#'],
      ['#','@','.','.','.','.','G','#'],
      ['#','#','.','#','#','@','#','#'],
      ['#','.','.','@','.','.','S','#'],
      ['#','@','.','.','.','.','.','#'],
      ['#','#','#','#','#','#','#','#']]


#�̷� ����ϱ�
def mazePrint(MAZE):
    for y in range(len(MAZE)):
        output = ''
        for x in range(len(MAZE[0])):
            output = output + MAZE[y][x]
        print output

#S�� ������ �Ǿ��ִ��� Ȯ��
def checkWall(x, y, MAZE):
    direction = ''
    if MAZE[y-1][x] != '#':
        direction += 'N'
    if MAZE[y+1][x] != '#':
        direction += 'S'
    if MAZE[y][x-1] != '#':
        direction += 'W'
    if MAZE[y][x+1] != '#':
        direction += 'E'
    return direction

#�����̱�
def move(moveWhere, MAZE):
    global x
    global y
    MAZE[y][x] = '.'
    if moveWhere == 'N':        
        y=y-1
    if moveWhere ==  'S':
        y=y+1
    if moveWhere == 'W':
        x=x-1
    if moveWhere == 'E':
        x=x+1

        
#@�� �������� �� S�� �ٲ��ְ� ���° üũ����Ʈ�������� �˷��ֱ�
def arrCheckPoint(MAZE, x, y):
    global checkPoint
    if (MAZE[y][x] == '@'):
        checkPoint = checkPoint +1
        MAZE[y][x] = 'S'
        english = ['first','second','third','forth','fifth','sixth','seventh','eightth']
        say = "You have arrived the %s checkpoint" %english[checkPoint-1]
        print say

#G�� �������� �� S�� �ٲ��ֱ�
def arriveG(MAZE, x, y):
    if (MAZE[y][x] == 'G'):
        MAZE[y][x] = 'S'
        return True
    else:
        return False

#.�� �����Ҷ� s�� �ٲ��ֱ�
def arrSpot(MAZE, x, y) :
     if MAZE[y][x] == '.':
         MAZE[y][x] = 'S'
    
# ������ ���� �ް� can't move Ȯ��
def moveNext(direction): #direction�� checkWall �Լ����� return�� ���� ���Ѵ�.
    global result
    global count
    while True:
        print ('Input next move: ('),
        print(',').join(direction),
        print (')?')
        if result == 1:
            break
        if count>20:
            break
        inputNext = raw_input().upper()
        if len(inputNext) != 1:
            print("Can't move!")
        elif inputNext not in direction:
            print("Can't move!")
        else:
            return inputNext
        
#�ʱⰪ����
x = 6
y = 3
checkPoint = 0
count = 0
result = 0

while True: #���ӽ���
    print str(count) + '>',
    if count > 20: #����Ƚ�� Ȯ��
        print "You lose!"
        
    else:
        arrCheckPoint(MAZE, x, y) #üũ����ƮȮ��
        if arriveG(MAZE, x, y): #G�� �����ߴ��� Ȯ��
            result = 1
            if checkPoint == 4 :
                print "You win!"
        
            else :                        
                print "You lose!"
        print "\n"

    mazePrint(MAZE) #�̷� ����ϱ�
    move(moveNext(checkWall(x, y, MAZE)), MAZE) #�����̰��ϱ�
    if count > 20:
        break
    if result == 1:
        break
    arrSpot(MAZE, x, y) #������ ǥ��
    count += 1 #Ƚ�� ����
