import log

if __name__ == '__main__':
    log.info('calling log.info from python')
    log.wtf('wtf call', leading_text='[script] ')

    # call a library function with ctypes, that does a log:
    log.lib.hello()
    log.trace('script end')
