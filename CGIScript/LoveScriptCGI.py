def compareNames(name1, name2):
	words = [name1, "love", name2]
	done = []
	array = []
	size = 0
	i = 0
	while i < len(words[0] + words[1] + words[2]):
		for w in words:
			for n in w:
				if not checkIfDone(n, done):
					x = compareCharNames(n, words)
					if x >= 10:
						array.append(x // 10)
						array.append(x % 10)
					else:
						array.append(x)
					done.append(n)
				size += 1
		i += 1  # Increment loop variable
	while len(array) > 2:
	    array = calculateValues(array)
	if len(array) == 2 and array[0] + array[1] < 6:
	    return array[0] + array[1]
	return array[0] * 10 + array[1]


def calculateValues(array):
	newArray = []
	for i in range(len(array) // 2):
		if array[i] + array[len(array) - i - 1] < 10:
			newArray.append(array[i] + array[len(array) - i - 1])
		else:
			newArray.append((array[i] + array[len(array) - i - 1]) // 10)
			newArray.append((array[i] + array[len(array) - i - 1]) % 10)
	if len(array) % 2 == 1:
		newArray.append(array[len(array) // 2])
	return newArray


def checkIfDone(c, array):
	if len(array) == 0:
		return False
	for item in array:
		if c == item:
		    return True
	return False


def compareCharNames(c, names):
    returnVal = 0
    for name in names:
        for char in name:
            if c == char:
                returnVal += 1
    return returnVal


def main():
	data = input("Insert first and second name: ")
	tab = data.split(" ")
	value = compareNames(tab[0], tab[1])
	if (tab[0] == "Leo" and tab[1] == "Julie") or (tab[1] == "Leo" and tab[0] == "Julie"):
		value = "miiiiiiiiille"
	print(tab[0], "loves", tab[1], "=", value, "%")


if __name__ == "__main__":
    main()