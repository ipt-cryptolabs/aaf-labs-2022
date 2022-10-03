package main

import (
	"fmt"

	"github.com/nochzato/set-invin/pkg/parser"
)

func main() {
	s := "create s1;"
	o := parser.Parse(s)
	fmt.Println(o)
}
