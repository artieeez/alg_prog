class Person:

    def __init__(self, nome, idade):
        self.nome = nome
        self.idade = idade

    def dizer_nome(self):
        print("Olá! Meu nome é {self.nome}")

p1 = Person("Artur", 22)

print(p1)



