from run import run
import readline

text = ''
while True:
    line = input('shit_DB > ')
    buffer = readline.get_line_buffer()
    if buffer:
        line += '\n' + buffer
    text += line

    if not line.strip():
        try:
          result, error = run(text)
          text = ''
          if error:
              print(error.as_string())
        except Exception as e:
          print("An error occurred:", e)
          continue
