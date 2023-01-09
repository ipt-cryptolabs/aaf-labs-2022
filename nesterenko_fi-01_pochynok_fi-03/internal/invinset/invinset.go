// Main data structure
package invinset

import (
	"fmt"
	"strconv"

	"github.com/nochzato/set-invin/nesterenko_fi-01_pochynok_fi-03/internal/sliceh"
)

type Invinset struct {
	Collections map[string]map[string][]int
	Invin       map[string]map[int][]string
}

func New() Invinset {
	invinset := Invinset{
		Collections: make(map[string]map[string][]int),
		Invin:       make(map[string]map[int][]string),
	}
	return invinset
}

func (invinset Invinset) ExecuteCommand(input map[string]string) {
	if input["command"] == "create" {
		invinset.Create(input["collectionName"])
	} else if input["command"] == "insert" {
		if len(input["values"]) == 0 {
			fmt.Println("Set can't be empty")
		} else {
			values := sliceh.StringToIntSlice(input["values"])
			invinset.Insert(input["collectionName"], values)
		}
	} else if input["command"] == "print_index" {
		invinset.PrintIndex(input["collectionName"])
	} else if input["command"] == "contains" {
		values := sliceh.StringToIntSlice(input["values"])
		fmt.Println(invinset.Contains(input["collectionName"], values))
	} else if input["command"] == "search" {
		if input["query"] != "" {
			if len(input["values"]) == 0 {
				fmt.Println("No values provided")
			} else {
				values := sliceh.StringToIntSlice(input["values"])
				invinset.Search(input["collectionName"], input["query"], values)
			}
		} else {
			invinset.Search(input["collectionName"], "", nil)
		}
	}
}

func (invinset Invinset) Create(collectionName string) {
	if _, keyExists := invinset.Collections[collectionName]; keyExists {
		fmt.Println("Collection " + collectionName + " already exists")
		return
	}

	invinset.Collections[collectionName] = make(map[string][]int)
	invinset.Invin[collectionName] = make(map[int][]string)
}

func (invinset Invinset) Insert(collectionName string, values []int) {
	if _, keyExists := invinset.Collections[collectionName]; !keyExists {
		fmt.Println("Collection " + collectionName + " doesn't exist")
		return
	}

	setName := "s" + string(strconv.Itoa(len(invinset.Collections[collectionName])+1))
	invinset.Collections[collectionName][setName] = sliceh.RemoveDuplicateInt(values)

	for _, number := range invinset.Collections[collectionName][setName] {
		_, keyExists := invinset.Invin[collectionName][number]
		if keyExists {
			invinset.Invin[collectionName][number] = append(invinset.Invin[collectionName][number], setName)
		} else {
			invinset.Invin[collectionName][number] = []string{setName}
		}
	}
}

func (invinset Invinset) PrintIndex(collectionName string) {
	if _, keyExists := invinset.Collections[collectionName]; !keyExists {
		fmt.Println("Collection " + collectionName + " doesn't exist")
		return
	}

	index := invinset.Invin[collectionName]
	for k, v := range index {
		var sets string
		for _, setName := range v {
			sets += setName + " "
		}
		fmt.Println(strconv.Itoa(k) + ": " + sets)
	}
}

func (invinset Invinset) Contains(collectionName string, values []int) bool {
	if _, keyExists := invinset.Collections[collectionName]; !keyExists {
		fmt.Println("Collection " + collectionName + " doesn't exist")
		return false
	}

	values = sliceh.RemoveDuplicateInt(values)
	for _, set := range invinset.Collections[collectionName] {
		if sliceh.AreEqual(set, values) {
			return true
		}
	}

	return false
}

func (invinset Invinset) Search(collectionName string, query string, values []int) {
	if _, keyExists := invinset.Collections[collectionName]; !keyExists {
		fmt.Println("Collection " + collectionName + " doesn't exist")
		return
	}

	if query == "" {
		for k, v := range invinset.Collections[collectionName] {
			var set string
			for _, number := range v {
				set += strconv.Itoa(number) + " "
			}
			fmt.Println(k + ": " + set)
		}
	} else if query == "intersects" {
		index := invinset.Invin[collectionName]
		sets := invinset.Collections[collectionName]
		setsToPrint := make(map[string][]int)

		for _, value := range values {
			matches := index[value]
			for _, match := range matches {
				setsToPrint[match] = sets[match]
			}
		}

		for k, v := range setsToPrint {
			var set string
			for _, number := range v {
				set += strconv.Itoa(number) + " "
			}
			fmt.Println(k + ": " + set)
		}

	} else if query == "contains" {
		index := invinset.Invin[collectionName]
		sets := invinset.Collections[collectionName]
		setsToPrint := make(map[string][]int)

		fullMatch := index[values[0]]

		for _, value := range values[1:] {
			matches := index[value]
			for idx, set := range fullMatch {
				if !sliceh.Contains(matches, set) {
					sliceh.Remove(fullMatch, idx)
				}
			}
		}

		for _, match := range fullMatch {
			setsToPrint[match] = sets[match]
		}

		for k, v := range setsToPrint {
			var set string
			for _, number := range v {
				set += strconv.Itoa(number) + " "
			}
			fmt.Println(k + ": " + set)
		}

	} else if query == "contained_by" {
		indexr := invinset.Invin[collectionName]
		index := make(map[int][]string)
		setsr := invinset.Collections[collectionName]
		sets := make(map[string][]int)
		setsToRemove := []string{}

		for k, v := range indexr {
			index[k] = v
		}

		for k, v := range setsr {
			sets[k] = v
		}

		for _, value := range values {
			delete(index, value)
		}

		for _, sets := range index {
			for _, set := range sets {
				if !sliceh.Contains(setsToRemove, set) {
					setsToRemove = append(setsToRemove, set)
				}
			}
		}

		for _, set := range setsToRemove {
			delete(sets, set)
		}

		for k, v := range sets {
			var set string
			for _, number := range v {
				set += strconv.Itoa(number) + " "
			}
			fmt.Println(k + ": " + set)
		}
	}
}
