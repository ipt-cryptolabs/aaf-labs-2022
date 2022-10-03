package parser

import (
	"regexp"
)

func Parse(input string) map[string]string {
	create_regex, _ := regexp.Compile(`(?i)\s*(?P<command>create)\s+(?P<collection_name>[a-zA-Z][a-zA-Z0-9_]*)\s*;`)

	insert_regex, _ := regexp.Compile(`(?i)\s*(?P<command>insert)\s+(?P<collection_name>[a-zA-Z][a-zA-Z0-9_]*)\s*{(?P<values>(\s*\d\s*,\s*)*\d\s*)};`)

	print_index_regex, _ := regexp.Compile(`(?i)\s*(?P<command>print_index)\s+(?P<collection_name>[a-zA-Z][a-zA-Z0-9_]*)\s*;`)

	contains_regex, _ := regexp.Compile(`(?i)\s*(?P<command>contains)\s+(?P<collection_name>[a-zA-Z][a-zA-Z0-9_]*)\s*{(?P<values>(\s*\d\s*,\s*)*\d\s*)};`)

	search_regex, _ := regexp.Compile(`(?i)\s*(?P<command>search)\s+(?P<collection_name>[a-zA-Z][a-zA-Z0-9_]*)\s*(where\s*(?P<query>(contains|contained_by|intersects))\s*{(?P<values>(\s*\d\s*,\s*)*\d\s*)})?;`)

	regexps := [5]*regexp.Regexp{create_regex, insert_regex, print_index_regex, contains_regex, search_regex}
	output := make(map[string]string)

	m := []string{}
	var valid *regexp.Regexp

	for i := 0; i < 5; i++ {
		m = regexps[i].FindStringSubmatch(input)
		if m != nil {
			valid = regexps[i]
			break
		}

		if i == 4 {

			return output
		}
	}

	for i, name := range valid.SubexpNames() {
		if i != 0 && name != "" {
			output[name] = m[i]
		}
	}

	return output
}
