from flask import Flask, request, Response
import html
app = Flask(__name__)

@app.route('/vuln')
def vuln():
    return 'hi ' + request.args.get('n', '')

@app.route('/safe')
def safe():
    body = 'hi ' + html.escape(request.args.get('n', ''))
    r = Response(body)
    r.headers['Content-Security-Policy'] = "default-src 'self'"
    r.headers['X-Content-Type-Options'] = 'nosniff'
    r.headers['X-Frame-Options'] = 'DENY'
    r.headers['Referrer-Policy'] = 'no-referrer'
    return r

if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5246)
