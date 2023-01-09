// Package for parsing input
package parser

import (
	"regexp"
	"strings"
)

func CompileRegexps() *[5]*regexp.Regexp {
	create_regexp, _ := regexp.Compile(`(?i)\s*(?P<command>create)\s+(?P<collectionName>[a-zA-Z][a-zA-Z0-9_]*)\s*;`)

	insert_regexp, _ := regexp.Compile(`(?i)\s*(?P<command>insert)\s+(?P<collectionName>[a-zA-Z][a-zA-Z0-9_]*)\s*{(?P<values>(\s*-?\d*\s*,\s*)*-?\d*\s*)}\s*;`)

	print_index_regexp, _ := regexp.Compile(`(?i)\s*(?P<command>print_index)\s+(?P<collectionName>[a-zA-Z][a-zA-Z0-9_]*)\s*;`)

	contains_regexp, _ := regexp.Compile(`(?i)\s*(?P<command>contains)\s+(?P<collectionName>[a-zA-Z][a-zA-Z0-9_]*)\s*{(?P<values>(\s*-?\d*\s*,\s*)*-?\d*\s*)}\s*;`)

	search_regexp, _ := regexp.Compile(`(?i)\s*(?P<command>search)\s+(?P<collectionName>[a-zA-Z][a-zA-Z0-9_]*)\s*(where\s*(?P<query>(contains|contained_by|intersects))\s*{(?P<values>(\s*-?\d*\s*,\s*)*-?\d*\s*)})?\s*;`)

	regexps := [5]*regexp.Regexp{create_regexp, insert_regexp, print_index_regexp, contains_regexp, search_regexp}

	return &regexps
}

func Parse(input string, regexps *[5]*regexp.Regexp) map[string]string {

	output := make(map[string]string)

	m := []string{}
	var valid *regexp.Regexp

	//looking for matchable regexp
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

	//creating a map
	for i, name := range valid.SubexpNames() {
		if i != 0 && name != "" {
			output[name] = m[i]
		}
	}

	//lowering all letters
	output["command"] = strings.ToLower(output["command"])

	//lowering all letters if query is specified
	if val, ok := output["query"]; ok {
		output["query"] = strings.ToLower(val)
	}

	//changing to readable view
	if val, ok := output["values"]; ok {
		val = strings.ReplaceAll(val, "\n", " ")
		val = strings.ReplaceAll(val, ",", " ")
		val = strings.TrimSpace(val)

		space := regexp.MustCompile(`\s+`)
		val = space.ReplaceAllString(val, " ")

		output["values"] = val
	}

	return output
}
