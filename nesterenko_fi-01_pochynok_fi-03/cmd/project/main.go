// Main package
package main

import (
	"bufio"
	"fmt"
	"os"

	"github.com/nochzato/set-invin/nesterenko_fi-01_pochynok_fi-03/internal/invinset"
	"github.com/nochzato/set-invin/nesterenko_fi-01_pochynok_fi-03/internal/parser"
)

func main() {
	//create instance of data structure
	invinset := invinset.New()

	//compilng regexps at the beggining of execution
	regexps := parser.CompileRegexps()

	//reading terminal
	for {
		reader := bufio.NewReader(os.Stdin)
		s, _ := reader.ReadString(';')
		o := parser.Parse(s, regexps)
		if len(o) == 0 {
			fmt.Println("Wrong input")
		} else {
			invinset.ExecuteCommand(o)
		}
	}
}
