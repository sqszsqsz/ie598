# IE598 Project Code - Zhe Sun
# 
from __future__ import division
from PIL import Image
import imagehash
import argparse
import shelve
import glob
import os
import re
import random
import time
import binascii
import hashlib
from bisect import bisect_right
from heapq import heappop, heappush

# construct the argument parse and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-d", "--dataset", required = True,
	help = "path to input dataset of images")
ap.add_argument("-d2", "--dataset2", required = True,
	help = "path to the second dataset of images")
args = vars(ap.parse_args())



# =============================================================================
#                 Generate MinHash Signatures
# =============================================================================
# Time this step.
print '\nGenerating random hash functions...'
# Record the maximum shingle ID that we assigned.
maxShingleID = 2**32-1
# We need the next largest prime number above 'maxShingleID'.
# I looked this value up here: 
# http://compoasso.free.fr/primelistweb/page/prime/liste_online_en.php
nextPrime = 4294967311
# Generate a list of random coefficients
def pickRandomCoeffs(k):
	# Create a list of 'k' random values.
	randList = []

	while k > 0:
	# Get a random shingle ID.
		randIndex = random.randint(0, maxShingleID) 

		# Ensure that each random number is unique.
		while randIndex in randList:
			randIndex = random.randint(0, maxShingleID) 

		# Add the random number to the list.
		randList.append(randIndex)
		k = k - 1
	return randList
 #------------------------------------------------
coeffA = pickRandomCoeffs(10)
coeffB = pickRandomCoeffs(10)

# List of documents represented as signature vectors
signatures = []

# Rather than generating a random permutation of all possible shingles, 
# we'll just hash the IDs of the shingles that are *actually in the document*,
# then take the lowest resulting hash code value. This corresponds to the index 
# of the first shingle that you would have encountered in the random order.

# For each document...
image_hashset = []
for imagePath in glob.glob(args["dataset"] + "/*.jpg"):
	# Get the hashfunction for the image
	image = Image.open(imagePath)
	h = str(imagehash.dhash(image))
	image_hashset.append(h)

image_hashset2 = []
for imagePath in glob.glob(args["dataset2"] + "/*.jpg"):
	# Get the hashfunction for the image
	image = Image.open(imagePath)
	h = str(imagehash.dhash(image))
	image_hashset2.append(h)

print '\nGenerating MinHash signatures for all images...'
signature1 = []
signature2 = []
# For each of the random hash functions...
for i in range(0, 10):
	# For each of the shingles actually in the document, calculate its hash code
	# using hash function 'i'. 

	# Track the lowest hash ID seen. Initialize 'minHashCode' to be greater than
	# the maximum possible value output by the hash.
	minHashCode1 = nextPrime + 1
	minHashCode2 = nextPrime + 1

	# For each shingle in the document...
	for image_hash in image_hashset:
		# Evaluate the hash function.
		image_ID = abs(hash(image_hash)) % (10 ** 8)
		hashCode = (coeffA[i] * image_ID + coeffB[i]) % nextPrime 

		# Track the lowest hash code seen.
		if hashCode < minHashCode1:
			minHashCode1 = hashCode

	# Add the smallest hash code value as component number 'i' of the signature.
	signature1.append(minHashCode1)

	for image_hash in image_hashset2:
		# Evaluate the hash function.
		image_ID = abs(hash(image_hash)) % (10 ** 8)
		hashCode = (coeffA[i] * image_ID + coeffB[i]) % nextPrime 

		# Track the lowest hash code seen.
		if hashCode < minHashCode2:
			minHashCode2 = hashCode

	# Add the smallest hash code value as component number 'i' of the signature.
	signature2.append(minHashCode2)

same_items = 0
for i in range(0, 10):
	if (signature1[i]==signature2[i]):
		same_items += 1
print ("\nEstimated Jaccard Similarity = " + str(same_items/10))


exact_num = len(set(image_hashset).intersection(image_hashset2))
exact_total = len(set(image_hashset).union(image_hashset2))

print("\nNumber of common images: "+ str(exact_num))
print("Number of total images: " + str(exact_total))
J = exact_num/exact_total
print("\nExact Jaccard Similarity = " + str(J))


