package main

import (
	"bufio"
	"fmt"
	"os"

	"github.com/nochzato/set-invin/nesterenko_fi-01_pochynok_fi-03/internal/parser"
)

func main() {
	//compilng regexps at the beggining of execution
	regexps := parser.CompileRegexps()

	//reading terminal
	for {
		reader := bufio.NewReader(os.Stdin)
		s, _ := reader.ReadString(';')
		o := parser.Parse(s, regexps)
		fmt.Println(o)
	}
}
