package parser

import (
	"reflect"
	"testing"
)

func TestCreate(t *testing.T) {
	s := "create s1;"
	regexps := CompileRegexps()
	want := make(map[string]string)
	want["command"] = "create"
	want["collection_name"] = "s1"
	got := Parse(s, regexps)

	if !reflect.DeepEqual(got, want) {
		t.Errorf("got %q, wanted %q", got, want)
	}
}
func TestInsert(t *testing.T) {
	s := "insert s1 {-1234, 2, 345};"
	regexps := CompileRegexps()
	want := make(map[string]string)
	want["command"] = "insert"
	want["collection_name"] = "s1"
	want["values"] = "-1234 2 345"
	got := Parse(s, regexps)

	if !reflect.DeepEqual(got, want) {
		t.Errorf("got %q, wanted %q", got, want)
	}
}
func TestPrint_index(t *testing.T) {
	s := "print_index s1;"
	regexps := CompileRegexps()
	want := make(map[string]string)
	want["command"] = "print_index"
	want["collection_name"] = "s1"
	got := Parse(s, regexps)

	if !reflect.DeepEqual(got, want) {
		t.Errorf("got %q, wanted %q", got, want)
	}
}
func TestContains(t *testing.T) {
	s := "contains s1 {1, 2234, -343};"
	regexps := CompileRegexps()
	want := make(map[string]string)
	want["command"] = "contains"
	want["collection_name"] = "s1"
	want["values"] = "1 2234 -343"
	got := Parse(s, regexps)

	if !reflect.DeepEqual(got, want) {
		t.Errorf("got %q, wanted %q", got, want)
	}
}

func TestSearchNoQuery(t *testing.T) {
	s := "search s1;"
	regexps := CompileRegexps()
	want := make(map[string]string)
	want["command"] = "search"
	want["collection_name"] = "s1"
	want["query"] = ""
	want["values"] = ""
	got := Parse(s, regexps)

	if !reflect.DeepEqual(got, want) {
		t.Errorf("got %q, wanted %q", got, want)
	}
}

func TestSearchQuery(t *testing.T) {
	s := "search s1 where contains {1, 2, 3};"
	regexps := CompileRegexps()
	want := make(map[string]string)
	want["command"] = "search"
	want["collection_name"] = "s1"
	want["query"] = "contains"
	want["values"] = "1 2 3"
	got := Parse(s, regexps)

	if !reflect.DeepEqual(got, want) {
		t.Errorf("got %q, wanted %q", got, want)
	}
}
func TestBozoInput(t *testing.T) {
	s := "InSeRt   \n   s1     \n {  1 , 2  , 3  };"
	regexps := CompileRegexps()
	want := make(map[string]string)
	want["command"] = "insert"
	want["collection_name"] = "s1"
	want["values"] = "1 2 3"
	got := Parse(s, regexps)

	if !reflect.DeepEqual(got, want) {
		t.Errorf("got %q, wanted %q", got, want)
	}
}
