// +build OMIT Golang tour
// Methods with pointer receivers take either a value or
// a pointer as the receiver when they are called.
// In general, all methods on a given type should have either
// value or pointer receivers, but not a mixture of both.
package main

import (
	"fmt"
	"math"
)

type Vertex struct {
	X, Y float64
}

func main() {
	v := Vertex{3, 4}
	v.Scale(5)
	fmt.Println("%v", v)

	p := &v
	p.Scale(2)
	fmt.Println("%v", v)

	fmt.Println(Abs(v))
}

// Classic function
func Abs(v Vertex) float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

// Methods can be defined for any named type
// (except a pointer or an interface); the receiver does not have to be a struct.

// Member method binded to the Vertex type
func (v *Vertex) Scale(f float64) {
	v.X = v.X * f
	v.Y = v.Y * f
}