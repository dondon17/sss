# Makefile
# 주석 처리는 #임을 주의

CC=gcc
CFLAGS=
OBJS=ex4.o
LIBS=

# 실행 파일의 이름을 정하는 부분
all: ex

ex: $(OBJS)
	$(CC) $(CFLAGS) -o ex $(OBJS) $(LIBS)

# object 파일이 어떤 코드의 obj 파일인지 구분
ex4.o: ex4.c
	$(CC) $(CFLAGS) -c ex4.c

# clean 역할이 뭔지 모르겠음
clean:
	rm -f $(OBJS) ex core