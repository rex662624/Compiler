.class public main
.super java/lang/Object

.method public static add()V
.limit stack 100
.limit locals 100
	ldc "Hello World"
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	return
.end method

.method public static main([Ljava/lang/String;)V
.limit stack 100
.limit locals 100
	
	invokestatic main/add()V
	ldc 0
	istore 0
FORLabel_0:
	iload 0
	ldc 10
	isub
	ifge Label_0
	iload 0
	ldc 1
	iadd
	istore 0
	iload 0
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	goto FORLabel_0
Label_0:
	ldc 0
	istore 0
FORLabel_1:
	iload 0
	ldc 15
	isub
	ifge Label_1
	iload 0
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	iload 0
	ldc 1
	iadd
	istore 0
	goto FORLabel_1
Label_1:
	ldc 18
	istore 0
FORLabel_2:
	iload 0
	ldc 3
	isub
	ifeq Label_2
	iload 0
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	iload 0
	ldc 1
	isub
	istore 0
	goto FORLabel_2
Label_2:
	return
.end method
