# IE598 Project Code - Zhe Sun
# Search similar images in a pre-built image database

# Worked off sample code found at 
# https://realpython.com/blog/python/fingerprinting-images-for-near-duplicate-detection/

# import the necessary packages
from PIL import Image
import imagehash
import argparse
import shelve
import distance

# construct the argument parse and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-d", "--dataset", required = True,
	help = "path to dataset of images")
ap.add_argument("-s", "--shelve", required = True,
	help = "output shelve database")
ap.add_argument("-q", "--query", required = True,
	help = "path to the query image")
ap.add_argument("-t", "--distance", required = True,
	help = "threshold hamming distance")
ap.add_argument("-f", "--hash", required = True,
	help = "hash type")
args = vars(ap.parse_args())

# open the shelve database
db = shelve.open(args["shelve"])

thres = int(args["distance"]);

# load the query image, compute the difference image hash, and
# and grab the images from the database that have the same hash
# value
query = Image.open(args["query"])
if (args["hash"]=="ahash"):
	h = str(imagehash.average_hash(query))
elif (args["hash"]=="phash"):
	h = str(imagehash.phash(query))
elif (args["hash"]	=="dhash"):
	h = str(imagehash.dhash(query))

filenames=[]

for image_entry in list(db):
	if (distance.hamming(h, image_entry) <= thres):
		# print(distance.hamming(h, image_entry))
		for entry in db[image_entry]:
			filenames.append(entry)

print(filenames)
print "Found %d images" % (len(filenames))

# loop over the images
for filename in filenames:
	# print(filename)
	image = Image.open(args["dataset"] + "/" + filename)
	image.show()

# close the shelve database
db.close()