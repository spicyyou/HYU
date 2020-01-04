#-*- coding: cp949 -*-ㅇ
MAZE=[['#','#','#','#','#','#','#','#'],
      ['#','@','.','.','.','.','G','#'],
      ['#','#','.','#','#','@','#','#'],
      ['#','.','.','@','.','.','S','#'],
      ['#','@','.','.','.','.','.','#'],
      ['#','#','#','#','#','#','#','#']]


#미로 출력하기
def mazePrint(MAZE):
    for y in range(len(MAZE)):
        output = ''
        for x in range(len(MAZE[0])):
            output = output + MAZE[y][x]
        print output

#S가 벽으로 되어있는지 확인
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

#움직이기
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

        
#@에 도착했을 때 S로 바꿔주고 몇번째 체크포인트지났는지 알려주기
def arrCheckPoint(MAZE, x, y):
    global checkPoint
    if (MAZE[y][x] == '@'):
        checkPoint = checkPoint +1
        MAZE[y][x] = 'S'
        english = ['first','second','third','forth','fifth','sixth','seventh','eightth']
        say = "You have arrived the %s checkpoint" %english[checkPoint-1]
        print say

#G에 도착했을 때 S로 바꿔주기
def arriveG(MAZE, x, y):
    if (MAZE[y][x] == 'G'):
        MAZE[y][x] = 'S'
        return True
    else:
        return False

#.에 도착할때 s로 바꿔주기
def arrSpot(MAZE, x, y) :
     if MAZE[y][x] == '.':
         MAZE[y][x] = 'S'
    
# 움직일 방향 받고 can't move 확인
def moveNext(direction): #direction은 checkWall 함수에서 return된 값을 말한다.
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
        
#초기값설정
x = 6
y = 3
checkPoint = 0
count = 0
result = 0

while True: #게임시작
    print str(count) + '>',
    if count > 20: #게임횟수 확인
        print "You lose!"
        
    else:
        arrCheckPoint(MAZE, x, y) #체크포인트확인
        if arriveG(MAZE, x, y): #G에 도착했는지 확인
            result = 1
            if checkPoint == 4 :
                print "You win!"
        
            else :                        
                print "You lose!"
        print "\n"

    mazePrint(MAZE) #미로 출력하기
    move(moveNext(checkWall(x, y, MAZE)), MAZE) #움직이게하기
    if count > 20:
        break
    if result == 1:
        break
    arrSpot(MAZE, x, y) #움직임 표시
    count += 1 #횟수 증가
