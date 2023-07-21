import random

def generate_test_case(array_size, lower_bound, upper_bound):
    if lower_bound > upper_bound:
        lower_bound, upper_bound = upper_bound, lower_bound

    array = [random.randint(lower_bound, upper_bound) for _ in range(array_size)]
    return array

def save_test_case_to_file(file_path, array_size, test_case):
    with open(file_path, "w") as file:
        file.write(str(array_size) + "\n")
        file.write(" ".join(str(num) for num in test_case))

def main():
    try:
        array_size = int(input("Tamanho do array: "))
        lower_bound = int(input("Limite inferior: "))
        upper_bound = int(input("Limite superior: "))

        test_case = generate_test_case(array_size, lower_bound, upper_bound)

        file_path = "teste05-5000000.txt"
        save_test_case_to_file(file_path, array_size, test_case)

        print(f"Caso de teste gerado e salvo em '{file_path}'.")

    except ValueError as e:
        print("Erro: Certifique-se de que você digitou números inteiros válidos.")

if __name__ == "__main__":
    main()