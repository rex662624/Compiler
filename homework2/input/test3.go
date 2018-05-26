var x int = 10

{
	var x int = 5
	x++
	println(x)
	{
		x++
		print(x)
	}
	var x int =8
}
var x int

println(x)

{
	var x int = 1
	{
		x++
		println(x)
		{
		x+=5
		println(x)
		}
	}
	print(x)
}

println(x)
