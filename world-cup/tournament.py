# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file
    with open(sys.argv[1], newline='') as f:
        # Reading from a csv file into dictionary by creating file object
        file = csv.DictReader(f)

        # Actual file reading
        for row in file:
            teams_dict = {'team': row['team'], 'rating': int(row['rating'])}
            teams.append(teams_dict)

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    for i in range(N):
        # Getting one winner at a time
        winners = simulate_tournament(teams)
        if winners in counts:
            # Calculating the number of times that team wins
            counts[winners] += 1
        else:
            # Adding new winning teams one by one
            counts.update({winners: 1})

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # Duplicating teams list
    winner = teams

    # Looping through unless there is only one winner
    while len(winner) != 1:
        winner = simulate_round(winner)

    str = winner[0]['team']
    # Returning winning team name
    return str


if __name__ == "__main__":
    main()
