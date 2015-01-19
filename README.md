# Go Markdown Parser

## Introduction

Not done yet.

### Way golang?

Because it has build-in UTF-8 support and could be compiled to executable file.

## How Does the Parser Work

There are four steps:
* Read file.
* Parse the block elements to construct the structure .
* Parse the span elements inside other elements.
* Translate to HTML and write to file.

### Basic Structure

```go
type Element struct {
	Structure int  // Document, leaf, container or inline.
	Function  int  // Specific type of the element.
	Open      bool // Used for parsing the structure of the document.
	Children  []IElement
	Inlines   []*UTF8String // Inline texts to be parsed.
}
```

### Basic Interface 

```go
type IElement interface {
	GetBase() *Element
	Translate(output chan<- string) // Translate to HTML.
	TryAppend(last IElement) bool   // Used for parsing the structure of the document.
	TryClose(last IElement) bool    // Used for parsing the structure of the document.
}
```
