from run import run


while True:
    text = input('shit_DB > ')
   
    result, error = run(text)

    if error:
        print(error.as_string())
    else:
        pass
        # print(result)
