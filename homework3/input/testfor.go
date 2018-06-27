var i int = 0

// single statment for, like C's while loop
for (i < 10) {
	i++
	println(i)
}
println("-------------1")
// C's for loop
for i = 0; i < 15; i++ {
	println(i)
}
println("-------------2")
for i = 18; i != 3; i-- {
	println(i)
}
println("-------------3")

for i = 2; i < 50; i=i+3+6.5 {
	println(i)
}

println("-------------4")
for i = 2; i < 10; i+=5 {
	println(i)
}

println("-------------5")
for i = 10; i > 0; i-=3.2-1 {
	println(i)
}

println("-------------6")
for i = 2; i < 20; i*=3 {
	println(i)
}

println("-------------7")
for i = 20; i >2; i/=5 {
	println(i)
}
