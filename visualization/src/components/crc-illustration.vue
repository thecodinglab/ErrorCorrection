<template>
  <illustration>
    <div v-for="row in rows" class="row">
      <p>{{ row.data }}<span class="append">{{ row.append }}</span></p>
      <div class="flex">
        <p v-html="getIndents(row.indents)"></p>
        <div>
          <p class="polynomial">{{ polynomial }}</p>
          <p>{{ row.solution }}</p>
        </div>
      </div>
    </div>
  </illustration>
</template>

<script>
  import Illustration from "../layouts/illustration";

  export default {
    name: "crc-illustration",
    components: {Illustration},
    props: ['bits'],
    data() {
      return {
        polynomial: '100011101',
        indents: 0
      }
    },
    computed: {
      rows() {
        const rows = [];
        const polynomial = this.polynomial;

        let data = '01011011'; // TODO: Set to this.bits
        let append = '';

        // First time add as many 0s as there are bits in polynomial
        for (let i = 0; i < polynomial.length; i++) {
          append += '0';
        }

        let normalized = data.substring(data.indexOf('1'), data.length) + append;
        const solution = this.XOR(polynomial, normalized);
        rows.push({data, append, indents: 0, solution});

        // Repeat for as long as there are appending 0s left
        while (append.length) {

          let indents;
          for (let i = 0; i < data.indexOf('1'); i++) {
            indents++;
            this.indents++;
          }

          // Append 0s to fit polynomial length
          append = '';
          for (let i = 0; i < polynomial.length - data.length; i++) {
            append += '0';
          }

          // XOR
          let normalized = data.substring(data.indexOf('1'), data.length) + append;
          const solution = this.XOR(polynomial, normalized);

          rows.push({data, append, indents, solution});
          data = solution;
        }

        return rows;
      }
    },
    methods: {
      XOR(polynomial, normalized) {
        let solution = '';
        for (let i = 0; i < polynomial.length; i++) {
          const p = polynomial.charAt(i) === '1';
          const n = normalized.charAt(i) === '1';
          const bool = (p && !n) || (!p && n);
          solution += bool ? '1' : '0';
        }
        return solution;
      },
      getIndents(range) {
        let indents = '';
        for (let i = 0; i < range; i++) {
          indents += '&nbsp;';
        }
        console.log(indents)
        return indents;
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

    .append {
      color: $light-gray;
    }

    .polynomial {
      color: $blue;
      border-bottom: 2px solid $light-gray;
      width: max-content;
      margin-bottom: 4px
    }

    .flex {
      display: flex;
    }
  }

</style>
