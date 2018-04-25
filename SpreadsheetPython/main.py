import csv

with open('2017 Retina Podcast Analytics.csv', 'r') as csvFile:
    csvReader = csv.reader(csvFile)

    next(csvReader)

    for line in csvReader:
        print line[3]
