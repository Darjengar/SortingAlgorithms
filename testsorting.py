import sorting

def main():
    liste = ['9','8','7','6','5','4','3','2', '0', '1']

    for iii in range(len(liste)):
        print(liste[iii] + ' ', end='')
    print()

    sorting.bubblesort(liste)

    for iii in range(len(liste)):
        print(liste[iii] + ' ', end='')
    print()

if __name__ == "__main__":
    main()