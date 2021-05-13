import requests
import sys
import os

#
# This is a python preprocessing program. This program can be used to download and set up the necessary tsv files 
# that are required to run the pagerank and spring embedder algorithms. The data that we are processing is a Reddit 
# subreddit hyperlink dataset from Stanford University.
# 

print("\n")

input_1 = input("Delete raw datasets after preprocessing (y/n)? ")
input_2 = input("Data for pagerank graph (0), data for force directed graph (1) or both (2)? ")

# download data from web
if not os.path.isfile("soc-redditHyperlinks-body.tsv") or not os.path.isfile("soc-redditHyperlinks-title.tsv"):
    print("\n")
    link = "http://snap.stanford.edu/data/soc-redditHyperlinks-body.tsv"
    file_name = "soc-redditHyperlinks-body.tsv"
    with open(file_name, "wb") as f:
        print("Downloading %s" % file_name)
        response = requests.get(link, stream=True)
        total_length = response.headers.get('content-length')
        if total_length is None: # no content length header
            f.write(response.content)
        else:
            dl = 0
            total_length = int(total_length)
            for data in response.iter_content(chunk_size=4096):
                dl += len(data)
                f.write(data)
                done = int(50 * dl / total_length)
                sys.stdout.write("\r[%s%s]" % ('=' * done, ' ' * (50-done)) )    
                sys.stdout.flush()
    print("\n")
    link = "http://snap.stanford.edu/data/soc-redditHyperlinks-title.tsv"
    file_name = "soc-redditHyperlinks-title.tsv"
    with open(file_name, "wb") as f:
        print("Downloading %s" % file_name)
        response = requests.get(link, stream=True)
        total_length = response.headers.get('content-length')
        if total_length is None: # no content length header
            f.write(response.content)
        else:
            dl = 0
            total_length = int(total_length)
            for data in response.iter_content(chunk_size=4096):
                dl += len(data)
                f.write(data)
                done = int(50 * dl / total_length)
                sys.stdout.write("\r[%s%s]" % ('=' * done, ' ' * (50-done)) )    
                sys.stdout.flush()
    print("\n")
print("\n")





# first preprocessing
print("Preprocessing...")
lines = []
with open("soc-redditHyperlinks-body.tsv") as body:
    for line in body:
        if line == "SOURCE_SUBREDDIT	TARGET_SUBREDDIT	POST_ID	TIMESTAMP	LINK_SENTIMENT	PROPERTIES\n":
            continue
        lines.append(line.split("\t")[0] + "\t" + line.split("\t")[1] + "\n")
with open("soc-redditHyperlinks-title.tsv") as title:
    for line in title:
        if line == "SOURCE_SUBREDDIT	TARGET_SUBREDDIT	POST_ID	TIMESTAMP	LINK_SENTIMENT	PROPERTIES\n":
            continue
        lines.append(line.split("\t")[0] + "\t" + line.split("\t")[1] + "\n")
# remove unnecessary files
if os.path.isfile("temp.tsv"):
    os.remove("temp.tsv")
if input_1 == 'y':
    if os.path.isfile("soc-redditHyperlinks-body.tsv"):
        os.remove("soc-redditHyperlinks-body.tsv")
    if os.path.isfile("soc-redditHyperlinks-title.tsv"):
        os.remove("soc-redditHyperlinks-title.tsv")
# write data to temp file
with open("temp.tsv", "w") as f:
    f.writelines(lines)





# pagerank preprocessing
if (input_2 == "0" or input_2 == "2"):
    pairs = dict()
    lines = []
    with open("temp.tsv", "r") as f:
        for l in f:
            line = l.rstrip("\n") # remove trailing '\n'
            if pairs.__contains__(line.split("\t")[0]):
                if not pairs[line.split("\t")[0]].__contains__(line.split("\t")[1]):
                    pairs[line.split("\t")[0]].append(line.split("\t")[1])
            else:
                pairs[line.split("\t")[0]] = [line.split("\t")[1]]
    for source in pairs:
        lines.append(source)
        index = len(lines) - 1
        for target in pairs[source]:
            lines[index] = lines[index] + "\t" + target
        lines[index] = lines[index] + "\n"
    # write data to final file
    with open("redditHyperlinksWithoutLengths.tsv", "w") as f:
        f.writelines(lines)





# force directed processing
if (input_2 == "1" or input_2 == "2"):
    pairs = dict()
    pairs_len = dict()
    lines = []
    with open("temp.tsv", "r") as f:
        for l in f:
            line = l.rstrip("\n") # remove trailing '\n'
            if pairs.__contains__(line.split("\t")[0]):
                if not pairs[line.split("\t")[0]].__contains__(line.split("\t")[1]):
                    pairs[line.split("\t")[0]].append(line.split("\t")[1])
                    pairs_len[line.split("\t")[0]].append("1")
                else:
                    pairs_len[line.split("\t")[0]][pairs[line.split("\t")[0]].index(line.split("\t")[1])] = str(int(pairs_len[line.split("\t")[0]][pairs[line.split("\t")[0]].index(line.split("\t")[1])]) + 1)
            else:
                pairs[line.split("\t")[0]] = [line.split("\t")[1]]
                pairs_len[line.split("\t")[0]] = ["1"]
    # remove unnecessary files
    if os.path.isfile("temp.tsv"):
        os.remove("temp.tsv")
    for source in pairs:
        for target in pairs[source]:
            lines.append(source)
            lines.append("\t" + target + "\t" + pairs_len[source][pairs[source].index(target)] + "\n")
    # write data to final file
    with open("redditHyperlinksWithLengths.tsv", "w") as f:
        f.writelines(lines)

print("Done\n")