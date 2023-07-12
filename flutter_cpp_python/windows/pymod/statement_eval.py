#coding:utf-8


def statement_eval(s: str) -> str:
    try:
        result = str(eval(s))
        return result
    except Exception as e:
        return str(e)


if __name__ == "__main__":
    # statement_eval("x=5;x+5")
    pass