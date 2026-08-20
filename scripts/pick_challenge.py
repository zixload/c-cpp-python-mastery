import json
import urllib.request
from datetime import datetime, timezone

now = datetime.now(timezone.utc)
month, day = now.month, now.day
doy = now.timetuple().tm_yday


def leetcode():
    req = urllib.request.Request(
        "https://leetcode.com/graphql",
        data=json.dumps(
            {"query": "query { activeDailyCodingChallengeQuestion { link question { title difficulty } } }"}
        ).encode(),
        headers={
            "Content-Type": "application/json",
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 "
            "(KHTML, like Gecko) Chrome/128.0 Safari/537.36",
        },
        method="POST",
    )
    with urllib.request.urlopen(req) as resp:
        data = json.load(resp)["data"]["activeDailyCodingChallengeQuestion"]
    title = data["question"]["title"]
    diff = data["question"]["difficulty"]
    link = "https://leetcode.com" + data["link"]
    return f"LeetCode - {title} ({diff})", link


def project_euler():
    n = 1 + (doy % 900)
    return f"Project Euler - Problem {n}", f"https://projecteuler.net/problem={n}"


def advent_of_code():
    year = now.year if month == 12 else now.year - 1
    return f"Advent of Code {year} - Day {day}", f"https://adventofcode.com/{year}/day/{day}"


if month == 12 and 1 <= day <= 25:
    label, link = advent_of_code()
elif doy % 2 == 0:
    try:
        label, link = leetcode()
    except Exception:
        label, link = project_euler()
else:
    label, link = project_euler()

print(f"{label}\n{link}")
