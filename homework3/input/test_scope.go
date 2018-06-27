var x int = 10

{
	var x int = 5
	x++
	println(x)
	{
		x++
		print(x)
	}

}


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

var y int = 10 
{
	var y int = 5
	y++
	println(y)

}
println(y)
{
	y++
	println(y)
	{
	y++
	println(y)
	var y int = 20
	y++
	println(y)

	}
}
println(y)