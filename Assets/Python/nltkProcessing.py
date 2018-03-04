import nltk

def nltkEntryProcess(entry_in):
    result_words = []
    result_pos = []
    tokens = nltk.word_tokenize(entry_in)
    tagged = nltk.pos_tag(tokens)

    for i in range(0, len(tagged)):
        result_words.append(tagged[i][0])
        result_pos.append(tagged[i][1])

    print('Entered words: ')
    print(result_words)
    print('Entered pos: ')
    print(result_pos)

nltkEntryProcess('ics')
nltkEntryProcess('Spicy peppers give food a nice kick')
nltkEntryProcess('That ugly man is an excellent woodworker')
