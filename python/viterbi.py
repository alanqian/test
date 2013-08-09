# http://en.wikipedia.org/wiki/Viterbi_algorithm
#
# When implementing Viterbi's algorithm, it should be noted that many languages use
# Floating Point arithmetic - as p is small, this may lead to underflow in the
# results. A common technique to avoid this is to take the logarithm of the
# probabilities and use it throughout the computation, the same technique used in the
# Logarithmic Number System. Once the algorithm has terminated, an accurate value can
# be obtained by performing the appropriate exponentiation.

states = ('Rainy', 'Sunny')

observations = ('walk', 'shop', 'clean')

start_probability = {'Rainy': 0.6, 'Sunny': 0.4}

transition_probability = {
   'Rainy' : {'Rainy': 0.7, 'Sunny': 0.3},
   'Sunny' : {'Rainy': 0.4, 'Sunny': 0.6},
   }

emission_probability = {
   'Rainy' : {'walk': 0.1, 'shop': 0.4, 'clean': 0.5},
   'Sunny' : {'walk': 0.6, 'shop': 0.3, 'clean': 0.1},
   }

# Helps visualize the steps of Viterbi.
def print_dptable(V):
    print "    ",
    for i in range(len(V)): print "%7s" % ("%d" % i),
    print

    for y in V[0].keys():
        print "%.5s: " % y,
        for t in range(len(V)):
            print "%.7s" % ("%f" % V[t][y]),
        print

# The function viterbi takes the following arguments: obs is the sequence of
# observations, e.g. ['walk', 'shop', 'clean']; states is the set of hidden states;
# start_p is the start probability; trans_p are the transition probabilities; and
# emit_p are the emission probabilities. For simplicity of code, we assume that the
# observation sequence obs is non-empty and that trans_p[i][j] and emit_p[i][j] is
# defined for all states i,j.
def viterbi(obs, states, start_p, trans_p, emit_p):
    V = [{}]
    path = {}

    # Initialize base cases (t == 0)
    for y in states:
        V[0][y] = start_p[y] * emit_p[y][obs[0]]
        path[y] = [y]

    # Run Viterbi for t > 0
    for t in range(1,len(obs)):
        V.append({})
        newpath = {}

        for y in states:
            (prob, state) = max([(V[t-1][y0] * trans_p[y0][y] * emit_p[y][obs[t]], y0) for y0 in states])
            V[t][y] = prob
            newpath[y] = path[state] + [y]

        # Don't need to remember the old paths
        path = newpath

    print_dptable(V)
    (prob, state) = max([(V[len(obs) - 1][y], y) for y in states])
    return (prob, path[state])

# In the running example, the forward/Viterbi algorithm is used as follows:
def example():
    return viterbi(observations,
                   states,
                   start_probability,
                   transition_probability,
                   emission_probability)
print example()

