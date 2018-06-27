var x int = 10

{
	var x int = 5
	x++
	println(x)//6
	{
		x++
		print(x)//7
	}

}


println(x)//10

{
	var x int = 1
	{
		x++
		println(x)//2
		{
		x+=5
		println(x)//7
		}
	}
	print(x)//7
}

println(x)//10

var y int = 10 
{
	var y int = 5
	y++
	println(y)//6

}
println(y)//10
{
	y++
	println(y)//11
	{
	y++
	println(y)//12
	var y int = 20
	y++
	println(y)//21

	}
}
println(y)//12