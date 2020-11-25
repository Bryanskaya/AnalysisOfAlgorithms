from faker import Faker
MAX_NUMBER = 1000

def generate_sites_passwords():
    unique_data = []
    '''count_net = 0
    count_ru = 0
    count_biz = 0
    count_com = 0
    count_org = 0
    count_info = 0
    count_io = 0'''

    fake = Faker()

    f = open('sites.txt', 'w')
    i = 0

    while i < MAX_NUMBER:
        url = fake.url()
        url = url.split('//')[1][: -1]

        temp = url.split('.')
        temp = temp[len(temp) - 1]

        if temp == 'com':
            if i % 3 == 1:
                url = url[: -3] + 'ru'
            elif i % 3 == 2:
                url = url[: -3] + 'io'

        if (url in unique_data):
            continue
        else:
            unique_data.append(url)

        password = fake.password(length=16, special_chars=True, digits=True, upper_case=True, lower_case=True)

        line = "{0} : {1}\n".format(
            url,
            password
        )

        '''temp = url.split('.')
        temp = temp[len(temp) - 1]
        print(temp)

        if temp == "net":
            count_net += 1
        elif temp == "ru":
            count_ru += 1
        elif temp == "biz":
            count_biz += 1
        elif temp == "com":
            count_com += 1
        elif temp == "org":
            count_org += 1
        elif temp == "info":
            count_info += 1
        elif temp == "io":
            count_io += 1'''

        f.write(line)
        i += 1
    f.close()
    #print(count_net, count_ru, count_biz, count_com, count_org, count_info, count_io)
if __name__ == "__main__":
    generate_sites_passwords()