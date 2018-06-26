.class public main
.super java/lang/Object

.method public static add(II)I
.limit stack 100
.limit locals 100
	iload 0
	iload 1
	iadd
	ireturn
.end method

.method public static main([Ljava/lang/String;)V
.limit stack 100
.limit locals 100
	ldc 0
	istore 0
	ldc 10
	ldc 5
	invokestatic main/add(II)I
	istore 0
	iload 0
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	return
.end method

