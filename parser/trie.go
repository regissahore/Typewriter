package parser

// This Trie is used for storing thousands of short words.
// It is used for HTML tags and named entities.
// The size of the next pointers increase dynamicly without order.
type Trie struct {
	char  []rune
	next  []*Trie
	value *UTF8String
}

func NewTrie() *Trie {
	return &Trie{make([]rune, 0), make([]*Trie, 0), nil}
}

func (node *Trie) AddWord(word *UTF8String, index int, value *UTF8String) {
	if index == word.Length() {
		node.value = value
		return
	}
	next := len(node.char)
	r := word.RuneAt(index)
	for i := 0; i < next; i++ {
		if node.char[i] == r {
			next = i
			break
		}
	}
	if next == len(node.char) {
		node.char = append(node.char, r)
		node.next = append(node.next, NewTrie())
	}
	node.next[next].AddWord(word, index+1, value)
}

func (node *Trie) FindWord(word *UTF8String, index int) (bool, *UTF8String) {
	if index == word.Length() {
		return node.value != nil, node.value
	}
	r := word.RuneAt(index)
	for i := 0; i < len(node.char); i++ {
		if node.char[i] == r {
			return node.next[i].FindWord(word, index+1)
		}
	}
	return false, nil
}
