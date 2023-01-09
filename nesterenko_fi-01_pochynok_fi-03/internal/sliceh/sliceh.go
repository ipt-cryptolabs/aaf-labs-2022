// Functions to help working with slices
package sliceh

import (
	"strconv"
)

func StringToIntSlice(s string) []int {
	result := []int{}
	var temp string

	for i := 0; i < len(s); i++ {
		if string(s[i]) != " " {
			temp += string(s[i])
		} else {
			number, _ := strconv.Atoi(temp)
			result = append(result, number)
			temp = ""
		}
	}

	number, _ := strconv.Atoi(temp)
	result = append(result, number)

	return result
}

func RemoveDuplicateInt(intSlice []int) []int {
	allKeys := make(map[int]bool)
	list := []int{}
	for _, item := range intSlice {
		if _, value := allKeys[item]; !value {
			allKeys[item] = true
			list = append(list, item)
		}
	}
	return list
}

func AreEqual(s1, s2 []int) bool {
	if len(s1) != len(s2) {
		return false
	}

	diff := make(map[int]int, len(s1))
	for _, _s1 := range s1 {
		diff[_s1]++
	}
	for _, _s2 := range s2 {
		if _, ok := diff[_s2]; !ok {
			return false
		}
		diff[_s2] -= 1
		if diff[_s2] == 0 {
			delete(diff, _s2)
		}
	}
	return len(diff) == 0
}

func Contains(s []string, e string) bool {
	for _, a := range s {
		if a == e {
			return true
		}
	}
	return false
}

func Remove(s []string, i int) []string {
	s[i] = s[len(s)-1]
	return s[:len(s)-1]
}
