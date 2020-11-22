from faker import Faker
MAX_NUMBER = 1000

def generate_sites_passwords():
    #fake_ru = Faker('ru_Ru')
    fake = Faker()

    f = open('sites.txt', 'w')

    for i in range(MAX_NUMBER):
        url = fake.url()
        password = fake.password(length=16, special_chars=True, digits=True, upper_case=True, lower_case=True)

        line = "{0} : {1}\n".format(
            url,
            password
        )

        f.write(line)
    f.close()

if __name__ == "__main__":
    generate_sites_passwords()