def spiral(dir, span):
    if dir < 1:
        return 1
    else:
        return (dir + span) * spiral((dir - 3), (1 - span))
    

if __name__ == '__main__':
    print(spiral(2, 180))