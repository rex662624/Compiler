.class public main
.super java/lang/Object
.method public static main([Ljava/lang/String;)V
.limit stack 100
.limit locals 100
	ldc "Hello World"
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
	ldc "Hello World"
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	ldc "123456"
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
	ldc 1
	ldc 2
	iadd
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	ldc 1
	ldc 2
	ldc 3
	imul
	iadd
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	ldc 3
	ldc 1
	ldc 2
	iadd
	imul
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	ldc 1
	ldc 2
	iadd
	ldc 5
	ldc 3
	irem
	imul
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	ldc 1.100000
	ldc 2
	i2f
	fadd
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(F)V
	ldc 8
	ldc 2
	idiv
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	ldc 8.500000
	ldc 2
	i2f
	fdiv
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(F)V
	ldc 8
	i2f
	ldc 2.500000
	fdiv
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(F)V
	ldc 8
	i2f
	ldc 2.500000
	fmul
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(F)V
	ldc 8.500000
	ldc 2
	i2f
	fmul
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(F)V
	ldc 8.800000
	ldc 2.500000
	fsub
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(F)V
	ldc 1
	ldc 2
	iadd
	ldc 3
	ldc 5
	imul
	iadd
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	ldc 5
	ldc 5
	iadd
	ldc 6
	ldc 8
	imul
	ldc 8
	idiv
	iadd
	ldc 9
	ldc 8
	iadd
	iadd
	ldc 5
	iadd
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	ldc 5
	ldc 8
	imul
	ldc 9
	ldc 8
	ldc 9
	imul
	iadd
	ldc 8
	ldc 9
	isub
	ldc 5
	iadd
	idiv
	iadd
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	ldc 5.500000
	ldc 9.900000
	ldc 85
	ldc 98
	ldc 8
	iadd
	idiv
	i2f
	fadd
	fmul
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(F)V
	ldc 5
	ldc 5
	iadd
	ldc 10
	iadd
	i2f
	ldc 8.500000
	fadd
	ldc 5.500000
	ldc 10
	i2f
	fmul
	fadd
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(F)V
	ldc 0
	istore 0
	ldc 5
	istore 1
	ldc 2.300000
	fstore 2
	fload 2
	ldc 2
	i2f
	fadd
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(F)V
	ldc 0
	istore 3
	iload 3
	ldc 1
	iadd
	istore 3
	iload 3
	ldc 1
	iadd
	istore 3
	iload 3
	ldc 2.200000
	f2i
	iadd
	istore 3
	iload 3
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	ldc 8.500000
	fstore 4
	fload 4
	ldc 2
	ldc 335
	iadd
	ldc 5
	imul
	ldc 8
	irem
	i2f
	fadd
	fstore 4
	fload 4
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(F)V
	ldc 0
	istore 5
	iload 5
	ldc 1
	iadd
	istore 5
	iload 5
	ldc 1
	iadd
	istore 5
	iload 5
	ldc 2.200000
	f2i
	iadd
	istore 5
	iload 5
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	iload 5
	ldc 2.200000
	f2i
	imul
	istore 5
	iload 5
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	iload 5
	ldc 2
	idiv
	istore 5
	iload 5
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	iload 5
	ldc 3
	irem
	istore 5
	iload 5
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	iload 5
	ldc 2.200000
	f2i
	iadd
	istore 5
	iload 5
	ldc 3.800000
	f2i
	isub
	istore 5
	iload 5
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	ldc 5
	i2f
	ldc 4.500000
	fcmpl
	ifeq Label_0
	ldc "True\n"
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	goto EXIT_0
Label_0:
	ldc "false\n"
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
EXIT_0:
	return
.end method
