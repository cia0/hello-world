import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.pos = set()
        self.neg = set()
        
        pfile = open(positives, "r") #add all the positive words into a set
        for line in pfile:
            if not line.startswith(';'):
                self.pos.add(line.rstrip("\n"))
        pfile.close()
        
        nfile = open(negatives, "r")#add all the negative words into a set
        for line in nfile:
            if not line.startswith(';'):
                self.neg.add(line.rstrip("\n"))
        nfile.close()
        return
        

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        score = 0
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        
        for token in tokens:
            if token.lower() in self.neg:
                score -= 1
            elif token.lower() in self.pos:
                score += 1

        return score
