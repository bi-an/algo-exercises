class TopVotedCandidate {

    private int[] times;
    private int[] winners;
    private Map<Integer, Integer> voteCounts; // person -> vote

    public TopVotedCandidate(int[] persons, int[] times) {
        int n = persons.length;

        this.times = times;
        winners = new int[n];
        voteCounts = new HashMap<>();

        int winner = -1;

        for (int i = 0; i < n; i++) {
            int p = persons[i];
            voteCounts.put(p, voteCounts.getOrDefault(p, 0) + 1);
            if (voteCounts.get(p) >= voteCounts.getOrDefault(winner, 0)) {
                winner = p;
            }
            winners[i] = winner;
        }
    }

    public int q(int t) {
        int left = 0, right = times.length - 1;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (times[mid] == t)
                return winners[mid];
            else if (times[mid] > t)
                right = mid - 1;
            else
                left = mid + 1;
        }

        return left > 0 ? winners[left - 1] : -1;
    }
}

/**
 * Your TopVotedCandidate object will be instantiated and called as such:
 * TopVotedCandidate obj = new TopVotedCandidate(persons, times);
 * int param_1 = obj.q(t);
 */
