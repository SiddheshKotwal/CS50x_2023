import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # getting cash of the user
    cashs = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])
    cash = cashs[0]["cash"]

    # getting all the data of the users portfolio
    details = db.execute("SELECT * FROM user_portfolio WHERE person_id = ?;", session["user_id"])
    sum = db.execute("SELECT SUM(total_price) FROM user_portfolio WHERE person_id = ?;", session["user_id"])
    price = sum[0]["SUM(total_price)"]

    # adding purchased price and the users wallet cash
    if price == None:
        grand_total = cash
    else:
        grand_total = price + cash

    # rendering the homepage to view users portfolio
    return render_template("index.html", details=details, cash=cash, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # for post request
    if request.method == "POST":

        # checking for all valid inputs
        if not request.form.get("symbol"):
            return apology("Invalid Symbol!", 400)

        try:
            if (not request.form.get("shares")) or (int(request.form.get("shares")) < 0):
                return apology("Invalid shares!", 400)
        except ValueError:
            return apology("Invalid shares!", 400)

        # getting stock price from the api
        stock = lookup(request.form.get("symbol"))
        if stock == None:
            return apology("Invalid Symbol!", 400)

        # checking for the valid purchase of the stock by comparing with the available wallet cash
        cash = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])
        if cash[0]["cash"] < (int(request.form.get("shares")) * int(stock["price"])):
            return apology("Can't Afford!", 403)

        # checking if the user already has the stock of that company
        prior_stock = db.execute("SELECT COUNT(*) FROM user_portfolio WHERE stock_symbol = ?;", request.form.get("symbol"))
        time = datetime.now()

        # if user has the stock of the same company giving the output on that basis
        if prior_stock[0]["COUNT(*)"] != 0:
            portfolio = db.execute("SELECT * FROM user_portfolio WHERE person_id = ?;", session["user_id"])
            prices = int(request.form.get("shares")) * stock["price"]
            sum_prices = prices + int(portfolio[0]["total_price"])
            new_number_of_shares = int(portfolio[0]["number_of_stocks"]) + int(request.form.get("shares"))
            db.execute("UPDATE users SET cash = ? WHERE id = ?;", (cash[0]["cash"] - prices), session["user_id"])
            db.execute("UPDATE user_portfolio SET number_of_stocks = ?, price_per_share = ?, total_price = ? WHERE person_id = ? AND stock_symbol = ?;",
                       new_number_of_shares, stock["price"], sum_prices, session["user_id"], request.form.get("symbol"))
            db.execute("INSERT INTO history (user_id, symbol, shares, price, transactions) VALUES (?, ?, ?, ?, ?);",
                       session["user_id"], request.form.get("symbol"), new_number_of_shares, prices, time)

        # else if user buys stock of the new company
        else:
            prices = int(request.form.get("shares")) * stock["price"]
            db.execute("UPDATE users SET cash = ? WHERE id = ?;", (cash[0]["cash"] - prices), session["user_id"])
            db.execute("INSERT INTO user_portfolio (person_id, stock_symbol, number_of_stocks, price_per_share, total_price) VALUES (?, ?, ?, ?, ?);",
                       session["user_id"], stock["symbol"], int(request.form.get("shares")), stock["price"], prices)
            db.execute("INSERT INTO history (user_id, symbol, shares, price, transactions) VALUES (?, ?, ?, ?, ?);",
                       session["user_id"], request.form.get("symbol"), int(request.form.get("shares")), prices, time)

        # after purchase redirecting to the homepage to show their portfolio
        return redirect("/")

    # for get request
    else:
        # rendering page of the purchase
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # getting all the data of the purchase/sell of the user
    history = db.execute("SELECT * FROM history WHERE user_id = ?;", session["user_id"])

    # rendering history of the users purchase/sell
    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    """ Changing Users Password"""

    # for post request
    if request.method == "POST":

        # checking for all valid inputs
        if not request.form.get("username"):
            return apology("Invalid Username!", 400)

        username = db.execute("SELECT username FROM users WHERE id = ?;", session["user_id"])
        # checking if the user exists
        if username[0]["username"] != request.form.get("username"):
            return apology("Invalid Username!", 400)

        if not request.form.get("Old_password"):
            return apology("Invalid Password!", 400)

        if not request.form.get("New_password"):
            return apology("Invalid Password!", 400)

        # getting the old password
        hash = db.execute("SELECT hash FROM users WHERE id = ? AND username = ?;", session["user_id"], request.form.get("username"))

        # checking if the old password is correct and changing it with the new password
        if check_password_hash(hash[0]["hash"], request.form.get("Old_password")):
            db.execute("UPDATE users SET hash = ? WHERE id = ? AND username = ?;", generate_password_hash(
                request.form.get("New_password"), "sha256"), session["user_id"], request.form.get("username"))
            return redirect("/logout")
        else:
            # else returning apology
            return apology("Invalid Password!", 403)

    # for get request
    else:
        # rendering page to change password
        return render_template("change_password.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # handling post request
    if request.method == "POST":

        # checking for all valid inputs
        if not request.form.get("symbol"):
            return apology("Invalid Symbol!", 400)

        # looking for the share price from api
        data = lookup(request.form.get("symbol"))
        if data == None:
            return apology("Invalid Symbol!", 400)

        name = data["name"]
        price = data["price"]
        symbol = data["symbol"]

        # outputing the share price of the requested company
        return render_template("quoted.html", name=name, price=price, symbol=symbol)

    # handling get request
    else:
        # rendering template to get the input
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # handling post request
    if request.method == "POST":

        # handling all Invalid inputs
        if not request.form.get("username"):
            return apology("Invalid username!", 400)

        if not request.form.get("password"):
            return apology("Invalid password!", 400)

        if not request.form.get("confirmation"):
            return apology("Invalid confirmation!", 400)

        # checking for confirmation of password
        if (request.form.get("password") != request.form.get("confirmation")):
            return apology("Password did not matched with confirmation!", 400)

        # checking if the username already exists and giving output with respect to it
        existing_username = db.execute("SELECT COUNT(*) FROM users WHERE username = ?;", request.form.get("username"))
        if existing_username[0]["COUNT(*)"] != 0:
            return apology("Username already exists choose other username!", 400)

        # inserting all registration details into database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?);", request.form.get(
            "username"), generate_password_hash(request.form.get("password"), "sha256"))

        # rendering login page
        return render_template("login.html")

    # handling get request
    else:
        # rendering template for registration
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # handling post request
    if request.method == "POST":

        # getting valid inputs
        if request.form.get("symbol") == None:
            return apology("Invalid symbol!", 400)

        if request.form.get("shares") == '':
            return apology("Invalid shares!", 400)
        try:
            if (int(request.form.get("shares")) < 0):
                return apology("Invalid shares!", 400)
        except ValueError:
            return apology("Invalid shares!", 400)

        # getting the number of shares the user has
        num = db.execute("SELECT number_of_stocks FROM user_portfolio WHERE person_id = ? AND stock_symbol = ?;",
                         session["user_id"], request.form.get("symbol"))
        number_of_shares = num[0]["number_of_stocks"]

        # checking if the user has enough shares to sell
        if number_of_shares < int(request.form.get("shares")):
            return apology("Invalid Input!", 400)

        # getting the cash user has spent on his stock purchase of that specific company
        amount = db.execute("SELECT total_price FROM user_portfolio WHERE stock_symbol = ? AND person_id = ?;",
                            request.form.get("symbol"), session["user_id"])

        total_price = amount[0]["total_price"]

        # getting current share price of the requested company
        share_price = lookup(request.form.get("symbol"))
        if share_price == None:
            return apology("Invalid Symbol!", 400)

        # getting price of the single share of that company
        single_price = share_price["price"]

        # calculating the amount user will get after selling the shares
        sell_amount = single_price * int(request.form.get("shares"))

        # getting total cash the user has in his wallet
        total_cash_ = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])
        total_cash = total_cash_[0]['cash']

        # updating the users portfolio database after selling shares
        db.execute("UPDATE user_portfolio SET total_price = ? WHERE stock_symbol = ? AND person_id = ?;",
                   (total_price - sell_amount), request.form.get("symbol"), session["user_id"])

        # updating the users database after selling shares (updation of users wallet cash)
        db.execute("UPDATE users SET cash = ? WHERE id = ?;", (total_cash + sell_amount), session["user_id"])

        # updation of the database of users portfolio by checking if the user has sold all of his shares of that particular company
        if (int(number_of_shares) - int(request.form.get("shares"))) == 0:
            db.execute("DELETE FROM user_portfolio WHERE stock_symbol = ? AND person_id = ?;",
                       request.form.get("symbol"), session["user_id"])

            # redirecting to the homepage to get updated portfolio
            return redirect("/")

        # if all shares are not sold
        else:
            # updation of the database of users portfolio
            db.execute("UPDATE user_portfolio SET number_of_stocks = ? WHERE person_id = ? AND stock_symbol = ?;",
                       (int(number_of_shares) - int(request.form.get("shares"))), session["user_id"], request.form.get("symbol"))

        # getting exact time when transactions performed
        transact_time = datetime.now()

        # inserting the data of the task performed in database(history)
        db.execute("INSERT INTO history (user_id, symbol, shares, price, transactions) VALUES (?, ?, ?, ?, ?);",
                   session["user_id"], request.form.get("symbol"), int(request.form.get("shares")) * -1, sell_amount, transact_time)

        # after selling shares redirecting to the homepage to get updated portfolio
        return redirect("/")

    # handling get request
    else:
        # getting all the companies symbols to display on the selling webpage
        stock_symbols = db.execute("SELECT stock_symbol FROM user_portfolio WHERE person_id = ?;", session["user_id"])

        # rendering selling webpage
        return render_template("sell.html", shares=stock_symbols)

