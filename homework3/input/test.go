println("Hello World")
print("Hello World")

println("123456")

//--------------

println(1+2)//3
println(1+2*3)//7
println(3*(1+2))//9
println((1+2)*(5%3))//6

println(1.1+2)//3.1

println(8/2)//4
println(8.5/2)//4.25
println(8/2.5)//3.2
println(8*2.5)//20
println(8.5*2)//17
println(8.8-2.5)//6.3

println(1+2+3*5)//18
println(5+5+6*8/8+(9+8)+5)//38
println(5*8+(9+8*9)/(8-9+5))//60
println(5.5*(9.9+(85/(98+8))))//54.45
println(5+5+10+8.5+5.5*10)//83.5
//--------------
var x int
var y int = 5
var z float32 = 2.3

println(z+2)
//---------------
var x2 int
x2=x2+1
x2+=1
x2+=2.2
println(x2)

var y2 float32 = 8.5
y2=y2+(2+335)*5%8//y+5
println(y2)
//-----------------
var x3 int
x3=x3+1
x3+=1
x3+=2.2
println(x3)//4

x3*=2.2
println(x3)//8
x3/=2
println(x3)//4
x3%=3
println(x3)//1
x3+=2.2//3
x3-=3.8//0
println(x3)//0
if (5!=4.5) {
	print("True\n")
} else{
	print("false\n")
}