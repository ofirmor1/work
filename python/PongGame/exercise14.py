text = "In mathematics, specifically category theory, a functor is a mapping between categories. Functors were "
"first considered in algebraic topology, where algebraic objects (such as the fundamental group) are "
"associated to topological spaces, and maps between these algebraic objects are associated to continuous"
" maps between spaces. Nowadays, functors are used throughout modern mathematics to relate various"
" categories. Thus, functors are important"
"in all areas within mathematics to which category theory is applied."

word_map = dict()

for word in text:
    if word not in word_map:
        word_map[word] = 1
    else:
        word_map[word] += 1
for word in word_map:
    print(f"{word} : {word_map[word]}", end="\n")
