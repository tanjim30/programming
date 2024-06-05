import itertools

def generate_match_schedule(teams):
    match_schedule = []
    team_combinations = list(itertools.combinations(teams, 2))

    # Schedule 2 matches for each team except one team which plays 6 matches
    for team in teams:
        if team != "TeamWith6Matches":
            team_matches = [(team, opponent) for (team, opponent) in team_combinations if team in (team, opponent)]
            match_schedule.extend(team_matches)
    
    # Schedule 6 matches for the team with 6 matches
    team_with_6_matches = "TeamWith6Matches"
    team_with_6_schedule = [(team_with_6_matches, opponent) for opponent in teams if opponent != team_with_6_matches]
    match_schedule.extend(team_with_6_schedule * 3)

    return match_schedule

# List of 4 teams in Group 1
group1_teams = ["Team1", "Team2", "Team3", "TeamWith6Matches"]

# Generate match schedule
schedule = generate_match_schedule(group1_teams)

# Display the match schedule
for match in schedule:
    print(f"{match[0]} vs {match[1]}")
