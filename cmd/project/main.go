package main

import (
	"bufio"
	"fmt"
	"os"

	"github.com/nochzato/set-invin/pkg/parser"
)

func main() {
	//compilng regexps at the beggining of execution
	regexps := parser.CompileRegexps()

	//reading terminal
	for {
		reader := bufio.NewReader(os.Stdin)
		s, _ := reader.ReadString('\n')
		o := parser.Parse(s, regexps)
		fmt.Println(o)
	}
}
