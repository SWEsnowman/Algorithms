from cs115 import*


'''December 2021'''


FILE ='musicrecplus.txt'






def dictionary(fileName):
    '''turns the data stored in the file into a dictionary'''
    file = open(fileName, 'r')
    userDict = {}
    for line in file:
        [username, bands] = line.strip().split(':')
        bandList = bands.split(',')
        bandList.sort()
        userDict[username] = bandList
    file.close()
    return userDict


preferences = dictionary(FILE)


def main():
    '''introduction to the program(where name is prompted)'''
    userDict = dictionary(FILE)
    username = input("Enter your name (put a $ symbol after your name if you wish your preferences to remain private): ")
    if not(username in userDict):
        preferences[username]=[]
        addPreferences(username)
    else:
        menu(username)


def menu(username):
    '''menu of the program where user can select service desired'''
    letter=input('Enter a letter to choose an option:\ne - Enter preferences\nr - Get recommendations\np - Show most popular artists\nh - How popular is the most popular\nm - Which user has the most likes\nq - Save and quit\n')
    if letter == 'e': addPreferences(username)
    elif letter == 'r': getRecommendations(username)
    elif letter == 'p': popularArtist(username)
    elif letter == 'h': howPopular(username)
    elif letter == 'm': mostLikes(username)
    elif letter == 'q': save()
    else: menu(username)


def addPreferences(name):
    '''where a user adds new artist preferences''' # doesn't work for new users to the system
    preferences[name] = []
    rec = input('Enter an artist that you like (Enter to finish): ')
    while rec != '':
        preferences[name] += [rec.strip().title()]
        rec = input('Enter an artist that you like (Enter to finish): ')
    preferences[name].sort()
    menu(name)


def numMatches(L,M):
    '''compares number of matches between two lists'''   
    count = 0
    i = 0
    j = 0
    # Invariant: count == number of matches between L[:i] and M[:j]
    while i < len(L) and j < len(M):
        if L[i]==M[j]:
            count += 1
            i += 1
            j += 1
        elif L[i] < M[j]:
            i += 1
        else:
            j += 1
    return count
    


def getRecommendations(user):
    '''prints the recommendations for a user'''
    closestUser=''
    biggestValue = 0
    for i in preferences:
        if i != user and not('$' in i) and preferences[i] != preferences[user]:
            
            value = numMatches(preferences[user],preferences[i])
            if value > biggestValue:
                
                biggestValue = value
                closestUser = i
           
           
    recList= []
    if closestUser == '':
        print('no recommendations available at ime.')
    else:
        for j in preferences[closestUser]:
            if j not in preferences[user]:
                recList= recList + [j]
        if recList == []:
            print('No recommendations available at this time.')
        else:
            for art in range(len(recList)):
                if recList!=[]:
                    print(recList[art])# need to know how to print different lines
    menu(user)# $ not working


def popularArtist(name):
    '''displays top three most popular artists'''
    artistCountDict={}
    for user in preferences:
        if '$' not in user:
            for artist in preferences[user]:
                if artist in artistCountDict:
                    artistCountDict[artist] +=1
                else: artistCountDict[artist] = 1
    if artistCountDict == {}:
        print('Sorry, no artists found.')
        menu(name)
    artistTuples=[]
    for i in artistCountDict:
        artistTuples=artistTuples + [(artistCountDict[i],i)]
    print(max(artistTuples)[1])
    artistTuples.remove(max(artistTuples))
    print(max(artistTuples)[1])
    artistTuples.remove(max(artistTuples))
    print(max(artistTuples)[1])
    menu(name)


def howPopular(name):
    '''displays top three most popular artists'''
    artistCountDict={}
    for user in preferences:
        if '$' not in user:
            for artist in preferences[user]:
                if artist in artistCountDict:
                    artistCountDict[artist] +=1
                else: artistCountDict[artist] = 1
    if artistCountDict == {}:
        print('Sorry, no artists found.')
        menu(name)
    artistTuples=[]
    for i in artistCountDict:
        artistTuples=artistTuples + [(artistCountDict[i],i)]
    print((max(artistTuples)[0]))
    menu(name)


def mostLikes(name):
    '''displays user who likes most artists'''
    count = 0
    winner = ''
    for user in preferences:
        curCount =len(preferences[user])
        if curCount > count:
            count = curCount
            winner = user
    if winner == '':
        print('Sorry, no user found.')
        menu(name)
    print(winner)
    menu(name)


def save():
    '''saves user preferences to file'''
    file = open(FILE, 'w')
    for name in preferences:
        toSave = str(name) + ':'+','.join(preferences[name]) +"\n"
        file.write(toSave)
    file.close()
    
if __name__ == '__main__': main()