using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Harvbot.Arms.Driver;

namespace Harvbot.Arms.ItemDetection
{
    public class NodeOffset
    {
        public HarvbotArmNodeTypes NodeType { get; set; }

        public int Offset { get; set; }
    }
}
