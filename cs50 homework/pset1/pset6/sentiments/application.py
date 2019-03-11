from flask import Flask, redirect, render_template, request, url_for
from analyzer import Analyzer
import helpers
import os
import sys

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name, 100)
    if tweets == None:
        return redirect(url_for("index"))
    
    # absolute paths to lists
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")

    # instantiate analyzer
    analyzer = Analyzer(positives, negatives)
        
    sentcount = [0,0,0]
    
    for tweet in tweets:
        score = analyzer.analyze(tweet)
        if score > 0.0:
            sentcount[0] += 1
        elif score < 0.0:
            sentcount[1] += 1
        else:
            sentcount[2] += 1

    # TODO
    total = sentcount[0] + sentcount[1] + sentcount[2]
    for count in sentcount:
        count = (count/total)*100.0
    positive, negative, neutral = sentcount[0], sentcount[1], sentcount[2]

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
