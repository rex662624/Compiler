var x int = 9

if (x == 10) {
   	x=80
	println(x)
} else if(x <= 10) {
 	x=50
	x++	
	println(x)//51
	if(x>80){
	println(x)
	} else{
			x=5
			println(x)//5
			if(x!=8){
					x++
					println(x)//6
				}
		}
} else if(x == 9) {
    	x = 20
	println(x)
} else {
    	x = 0
	println(x)
}
			if(x!=8){
					x=0
					println(x)//0
				}