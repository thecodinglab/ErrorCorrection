<template>
  <illustration>
    <button @click="play">Play</button>
    <button @click="tick">Tick</button>
    <button @click="playback.step = 0">Clear</button>
    <div v-for="(row, i) in rows" class="flex row">
      <p v-html="getIndents(row.indents)"></p>
      <div>
        <p v-if="i === 0">{{ row.data }}<span class="append">{{ appending }}</span></p>
        <p v-else>{{ row.data }}<span class="append">{{ row.append }}</span></p>
        <div class="flex">
          <p v-html="getIndents(row.indent)"></p>
          <tooltip tooltip="Polynomial">
            <p class="polynomial">{{ polynomial }}</p>
          </tooltip>
        </div>
      </div>
    </div>
    <div class="flex row">
      <p v-html="getIndents(indents)"></p>
      <p class="solution"><span class="append">{{ solution.prepend }}</span>{{ solution.data }}{{ solution.append }}</p>
    </div>
  </illustration>
</template>

<script>
  import Illustration from "../layouts/illustration";
  import Tooltip from "./tooltip";

  export default {
    name: "crc-illustration",
    components: {Tooltip, Illustration},
    props: ['bits'],
    data() {
      return {
        polynomial: '110101',
        solution: '',
        indents: 0,
        playback: {
          running: false,
          speed: 1000,
          interval: null,
          step: 0
        }
      }
    },
    computed: {
      rows() {
        const rows = [];
        const polynomial = this.polynomial;

        let data = '100111010101010101010101010101'; // TODO: Set to this.bits
        let indents = 0;
        let length = data.length + polynomial.length - 1;

        while (true) {
          const indent = data.indexOf('1');

          let append = '';
          for (let i = 0; i < polynomial.length - (data.length - indent); i++) {
            append += '0';
          }

          rows.push({data, append, indent, indents});
          indents += indent;

          // XOR
          const normalized = data.substring(indent) + append;
          data = '';
          for (let i = 0; i < polynomial.length; i++) {
            data += parseInt(polynomial.charAt(i)) ^ parseInt(normalized.charAt(i));
          }

          console.log(indents + ' + ' + polynomial.length + ' >= ' + length)
          if ((indents + 1) + polynomial.length >= length) {
            const prepend = this.fill('0', length - (indents + polynomial.length - 1));
            const d = data.substring(prepend.length);
            const append = this.fill('0', (polynomial.length - 1) - d.length)

            this.solution = {
              data: d,
              prepend,
              append
            };
            this.indents = indents;
            break;
          }
        }

        return rows;
      },
      appending() {
        let append = '';
        for (let i = 0; i < this.polynomial.length - 1; i++) {
          append += '0';
        }
        return append;
      }
    },
    methods: {
      fill(string, range) {
        let zeroes = '';
        for (let i = 0; i < range; i++) zeroes += string;
        return zeroes;
      },
      getIndents(range) {
        return this.fill('&nbsp;', range)
      },
      play() {
        let playback = this.playback;
        if (playback.running = !playback.running) {
          playback.interval = setInterval(this.tick, playback.speed);
        } else {
          clearInterval(playback.interval);
        }
        console.log(playback.running)
      },
      tick() {
        this.playback.step++;
      }
    }
  }
</script>

<style lang="scss" scoped>
  @import "../color-palette";

  .row {
    p {
      margin: 0;
      letter-spacing: 2px;
    }

    .data {

    }

    .polynomial {
      color: $blue;
      border-bottom: 2px solid $light-gray;
      width: max-content;
    }

  }

  .solution {
    
  }

  .append {
    color: $light-gray;
  }

  .flex {
    display: flex;
  }

</style>
